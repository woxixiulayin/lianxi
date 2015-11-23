from flask.ext.sqlalchemy import SQLAlchemy
from datetime import datetime

db = SQLAlchemy()

count = 0


class Blog(db.Model):

    id = db.Column(
        db.Integer, primary_key=True, unique=True)
    title = db.Column(db.String(50),  unique=True)
    time_creat = db.Column(db.DateTime, default=datetime.now)
    content = db.Column(db.String())

    def __init__(self, title, content):
        self.title = title
        self.content = content
        self.id = Blog.next_id()

    @staticmethod
    def next_id():
        return len(Blog.query.all()) + 1
