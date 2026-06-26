from datetime import datetime
from typing import Optional
from pydantic import BaseModel

class FileDTO(BaseModel):
    id: int
    name: str
    path: str
    owner_id: int
    created_at: datetime

class FileCreateDTO(BaseModel):
    name: str
    path: str
    owner_id: int

class FileUpdateDTO(BaseModel):
    name: Optional[str] = None
