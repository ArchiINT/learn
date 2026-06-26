from datetime import datetime
from typing import Optional

from pydantic import BaseModel, ConfigDict


class FileCreateSchema(BaseModel):
    name: str
    path: str

class FileResponseSchema(BaseModel):
    id: int
    name: str
    path: str
    owner_id: int
    created_at: datetime
    model_config = ConfigDict(from_attributes=True) # Pydantic should can read Objects atribute to return json 

class FileUpdateSchema(BaseModel):
    name: Optional[str] = None