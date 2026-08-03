# 📚 База знаний

> Личные заметки по темам, которые разобрал. Читай красиво: `glow knowledge/`

---

## Как читать

```bash
glow knowledge/                # меню всех заметок, выбор стрелками
glow knowledge/<файл>.md       # конкретная заметка (выход q)
```

Подробнее про просмотр Markdown в терминале → [`md_commands.md`](md_commands.md).

---

## Заметки

### 🖥 Low-Level / архитектура

| Файл | О чём |
|---|---|
| [`cpu_architectures_and_compatibility.md`](cpu_architectures_and_compatibility.md) | x86 / ARM / RISC-V, CISC vs RISC, почему код не переносится между архитектурами, слои перевода (Rosetta, Wine, Proton, box64), графические API (DirectX / Metal / OpenGL / Vulkan), почему Mac силён в графике но слаб в играх |

### 🐍 File Server (FastAPI)

| Файл | О чём |
|---|---|
| [`dto_vs_schema_vs_model.md`](dto_vs_schema_vs_model.md) | Зачем разделять Pydantic Schema, DTO и SQLAlchemy Model — три объекта для трёх слоёв (HTTP / Domain / Database) |
| [`file_server_progress.md`](file_server_progress.md) | Прогресс проекта Cloud File Storage: что сделано, следующие шаги, путь к проекту |

### 🛠 Инструменты / терминал

| Файл | О чём |
|---|---|
| [`md_commands.md`](md_commands.md) | Красивый просмотр Markdown в терминале: `glow` (рендер) vs `bat` (подсветка), флаги, фишки, алиасы для `~/.zshrc` |

---

## Как добавлять новую заметку

1. Создать `knowledge/<тема>.md` (стиль как у остальных: `#` заголовок, `>` подзаголовок, таблицы, шпаргалка в конце).
2. Добавить строку в таблицу выше — в подходящую секцию.
3. Читать через `glow knowledge/`.
