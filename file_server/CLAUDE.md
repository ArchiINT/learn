# Cloud File Storage — учебный проект

Учебный FastAPI-проект. Студент — начинающий разработчик, знает FastAPI/Flask, базовый JS, C, ESP32. Роль Claude — ментор: объяснять ПОЧЕМУ, а не просто давать код. Студент пишет сам, Claude проверяет и направляет.

## Стек
- FastAPI + uvicorn
- SQLAlchemy + Alembic + psycopg2 (PostgreSQL)
- JWT (python-jose) + passlib[bcrypt]
- pydantic-settings для конфига
- Docker (позже)

## Структура
```
app/
  api/v1/          — эндпоинты (auth.py, files.py) — ПУСТЫЕ
  core/
    config.py      — Settings через pydantic-settings — ГОТОВО
    security.py    — JWT логика — ПУСТОЙ
  db/
    models/user.py — SQLAlchemy модель — ПУСТОЙ
    models/file.py — SQLAlchemy модель — ПУСТОЙ
    session.py     — подключение к БД — ПУСТОЙ
  domain/
    user/dto.py, exceptions.py   — ПУСТЫЕ
    file/dto.py, exceptions.py   — ПУСТЫЕ
  repositories/
    abstract.py                      — абстрактный репо — ПУСТОЙ
    postgres/user_repo.py            — ПУСТОЙ
    file_system/file_repo.py         — ПУСТОЙ
  schemas/
    user.py        — Pydantic схемы — ПУСТОЙ
    file.py        — Pydantic схемы — есть черновик User (нужно переделать)
  main.py          — bare FastAPI() — почти пустой
```

## Архитектурный план
- Паттерн Repository: абстрактный интерфейс → реализации (postgres для users, filesystem для files)
- Domain слой: DTO + исключения для каждой сущности
- Авторизация через JWT, все файловые эндпоинты требуют токен

## Спроектированные эндпоинты (endpoints.txt)
**Files:** GET /files, GET /files/{id}, GET /files/{id}/download, POST /files/upload, PUT /files/{id}, DELETE /files/{id}
**Users:** GET /users, GET /users/{id}, PUT /users/{id}, DELETE /users/{id}
**Auth:** POST /auth/register, POST /auth/login

## Что нужно сделать (в порядке)
1. `.env` — сгенерировать SECRET_KEY: `openssl rand -hex 32`
2. `app/db/models/user.py` и `app/db/models/file.py` — SQLAlchemy модели
3. `app/db/session.py` — engine + SessionLocal + Base
4. `app/core/security.py` — hash_password, verify_password, create_access_token, decode_token
5. `app/domain/user/dto.py` и `app/domain/file/dto.py` — Pydantic DTO
6. `app/schemas/user.py`, `app/schemas/file.py` — схемы для запросов/ответов
7. `app/repositories/abstract.py` — абстрактный CRUD
8. `app/repositories/postgres/user_repo.py` — реализация для юзеров
9. `app/repositories/file_system/file_repo.py` — реализация для файлов
10. `app/api/v1/auth.py` и `app/api/v1/files.py` — роуты
11. `app/main.py` — подключить роутеры, настроить приложение
12. Alembic миграции
13. Docker + docker-compose

## Заметки
- `.env` не коммитится (в .gitignore)
- `venv/` не коммитится
- Проект личного использования — в будущем планируется auth через VPN или IP whitelist
