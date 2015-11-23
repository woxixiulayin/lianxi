from flask import Flask, request, redirect,\
    render_template, session, flash, abort, url_for
from my_db import *

# configuration
SQLALCHEMY_DATABASE_URI = 'sqlite:////home/lzg/work/lianxi/flaskr/db/flaskr.db'
DEBUG = True
USERNAME = 'liu'
PASSWORD = 'liu'
SECRET_KEY = 'very secret'
HOST = '0.0.0.0'

# creat app
app = Flask(__name__)
app.config.from_object(__name__)
db.init_app(app)
db.app = app
db.create_all()


@app.route('/')
def show_enties():
    entries = Blog.query.all()
    for e in entries:
        print e.title
    return render_template('show_enties.html', entries=entries)


@app.route('/add', methods=['POST'])
def add_entry():
    if not session.get('logged_in'):
        abort(401)
    blog = Blog(title=request.form['title'],
                content=request.form['content'])
    db.session.add(blog)
    db.session.commit()

    flash('new entry was successfully posted')
    return redirect(url_for('show_enties'))


@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        if request.form['username'] != app.config['USERNAME']:
            error = 'Invalid username'
        elif request.form['password'] != app.config['PASSWORD']:
            error = 'Invalid password'
        else:
            session['logged_in'] = True
            flash('you were logged in')
            return redirect(url_for('show_enties'))

    return render_template('login.html', errr=error)


@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    flash('you were logged out')
    return redirect(url_for('show_enties'))

if __name__ == '__main__':
    app.run()
    # from livereload import Server
    # server = Server(app)
    # server.serve()
