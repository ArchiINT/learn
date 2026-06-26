from datetime import UTC, datetime, timedelta
from passlib.hash import bcrypt
from jose import jwt

from app.core.config import settings

def hash_password(password: str):
    return bcrypt.hash(password)

def verify_password(plain, hashed):
    return bcrypt.verify(plain, hashed)
    
def create_access_token(data: dict) -> str:
    payload = data.copy()
    exp = datetime.now(UTC) + timedelta(minutes=settings.ACCESS_TOKEN_EXPIRE_MINUTES)
    payload["exp"] = exp
    return jwt.encode(payload, settings.SECRET_KEY, algorithm=settings.ALGORITHM)

def decode_token(token: str) -> dict:
    return jwt.decode(token, settings.SECRET_KEY, algorithms=[settings.ALGORITHM])