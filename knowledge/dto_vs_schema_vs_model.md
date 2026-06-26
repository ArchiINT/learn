# DTO vs Pydantic Schema vs SQLAlchemy Model

> Зачем их разделять и как они работают вместе в FastAPI проекте

---

## Короткий ответ

В FastAPI проекте одну и ту же сущность (например "файл") описывают **три разных объекта** — каждый для своего слоя:

| Слой     | Объект           | Для чего                          |
|----------|------------------|-----------------------------------|
| HTTP     | Pydantic Schema  | Принять / отдать данные по сети   |
| Domain   | DTO (dataclass)  | Передавать данные внутри кода     |
| Database | SQLAlchemy Model | Хранить данные в таблице          |

---

## Как выглядит каждый из них

### 1. Pydantic Schema — `schemas/file.py`

```python
from pydantic import BaseModel
from datetime import datetime

class FileCreateSchema(BaseModel):
    """Принимаем от клиента при загрузке файла"""
    name: str

class FileSchema(BaseModel):
    """Отдаём клиенту в ответе"""
    id: int
    name: str
    size: int
    uploaded_at: datetime
    owner_id: int

    model_config = {"from_attributes": True}  # чтобы читать из SQLAlchemy объектов
```

### 2. DTO — `domain/file/dto.py`

```python
from dataclasses import dataclass
from typing import Optional

@dataclass(slots=True)
class FileDTO:
    """Результат — то что возвращает репозиторий"""
    id: int
    name: str
    size: int
    owner_id: int

@dataclass(slots=True)
class FileCreateDTO:
    """Создать файл — то что передаём в репозиторий"""
    name: str
    size: int
    owner_id: int

@dataclass(slots=True)
class FileUpdateDTO:
    """Обновить файл — необязательные поля"""
    name: Optional[str] = None
```

### 3. SQLAlchemy Model — `db/models/file.py`

```python
from sqlalchemy import Column, Integer, String, DateTime, ForeignKey
from sqlalchemy.sql import func
from db.session import Base

class FileModel(Base):
    __tablename__ = "files"

    id          = Column(Integer, primary_key=True)
    name        = Column(String, nullable=False)
    path        = Column(String, nullable=False)
    size        = Column(Integer, nullable=False)
    owner_id    = Column(Integer, ForeignKey("users.id"))
    uploaded_at = Column(DateTime, server_default=func.now())
```

---

## Как они работают вместе — полный путь запроса

```
[Клиент]       POST /files/upload  { name: "photo.jpg" }
    ↓
[Роутер]       FileCreateSchema — Pydantic валидирует данные
    ↓
[Роутер]       Schema → DTO, передаём в репозиторий
    ↓
[Репозиторий]  создаёт FileModel, сохраняет в БД
    ↓
[Репозиторий]  возвращает FileDTO (не SQLAlchemy объект!)
    ↓
[Роутер]       DTO → Schema, оборачиваем для ответа
    ↓
[Клиент]       { id, name, size, uploaded_at, owner_id }
```

### Код роутера

```python
@router.post("/upload", response_model=FileSchema)
async def upload_file(
    payload: FileCreateSchema,
    current_user: UserDTO = Depends(get_current_user),
    repo: AbstractFileRepository = Depends(get_file_repo),
):
    # Schema → DTO (переходим из HTTP слоя в domain слой)
    dto = FileCreateDTO(
        name=payload.name,
        size=payload.size,
        owner_id=current_user.id,
    )

    # Репозиторий работает только с DTO — он не знает о Pydantic
    file_dto = repo.create(dto)

    # DTO → Schema (возвращаемся в HTTP слой для ответа)
    return FileSchema(
        id=file_dto.id,
        name=file_dto.name,
        size=file_dto.size,
        uploaded_at=file_dto.uploaded_at,
        owner_id=file_dto.owner_id,
    )
```

---

## Зачем вообще разделять?

Если репозиторий принимает Pydantic Schema напрямую:

```python
def create(self, payload: FileCreateSchema): ...  # ❌ плохо
```

Тогда везде где нужен репозиторий — тащишь HTTP объект:

```python
# В тесте
repo.create(FileCreateSchema(name="test.txt"))    # HTTP объект в тесте — зачем?

# В скрипте бэкапа по крону
repo.create(FileCreateSchema(name="backup.zip"))  # HTTP объект там где нет HTTP
```

С DTO всё чисто — репозиторий не знает откуда пришёл вызов:

```python
# В роутере, в тесте, в скрипте — одинаково:
repo.create(FileCreateDTO(name="photo.jpg", size=100, owner_id=1))  # ✅
```

---

## Правило для запоминания

```
Pydantic Schema  →  разговаривает с интернетом
DTO              →  разговаривает с кодом
SQLAlchemy Model →  разговаривает с базой данных
```

Каждый слой знает только о своём соседе. Никогда не прыгаем через слой:

```
Schema → DTO → Model     ✅
Schema → Model           ❌
```

---

## Когда можно не разделять?

В маленьких проектах (прототип, хакатон) можно передавать Pydantic Schema
прямо в репозиторий — это нормально.

Но как только появляются:
- тесты
- несколько разработчиков
- сложная бизнес-логика

— разделение окупается с первого же рефактора.
