from datetime import datetime
from sqlalchemy import DateTime, ForeignKey, Integer, Column, String 
from app.db.session import Base

class File(Base):
    __tablename__ = "files"
    id = Column(Integer(), primary_key=True)
    name = Column(String(100), nullable=False)
    path = Column(String(200), nullable=False)
    owner_id = Column(ForeignKey("users.id"), nullable=False)
    created_at = Column(DateTime(), default=datetime.now)
    