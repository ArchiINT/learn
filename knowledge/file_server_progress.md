# File Server Project — Прогресс

## Что сделано

- [x] Спроектировали структуру проекта
- [x] Разобрали архитектуру: Schema → DTO → SQLAlchemy Model
- [x] Написали эндпоинты (`file_server/endpoints.txt`)
- [x] Создали структуру папок через терминал
- [x] Настроили venv, установили зависимости (`requirements.txt`)
- [x] Написали `app/core/config.py` (pydantic-settings)

## Следующий шаг

- [ ] Заполнить `.env` файл — сгенерировать SECRET_KEY: `openssl rand -hex 32`
- [ ] Написать `app/db/models/user.py` — SQLAlchemy модель пользователя
- [ ] Написать `app/db/models/file.py` — SQLAlchemy модель файла
- [ ] `app/db/session.py` — подключение к БД

## Путь к проекту

`/home/vi/learn/file_server/`
