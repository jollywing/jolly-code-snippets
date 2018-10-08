# encoding:utf-8

from bottle import route, run, static_file, request
import sqlite3

@route('/index')
@route('/main')
@route('/index.html')
def index():
    return static_file('index.html', root='./static')

@route('/get_heroes_list/:name')
def heroes_list(name):
    # connect sqlite db
    conn = sqlite3.connect('heroes.db')
    c = conn.cursor()
    # execute sql
    sql = 'SELECT name FROM heroes WHERE race="%s";'% name
    print sql
    c.execute(sql);
    heroes = []
    for row in c:
        heroes.append(row[0])
    # close db
    conn.close()
    # construct response
    hero_list = "<select id='hero_select' name='hero' onchange='on_hero_selected()'>"
    hero_list += u"<option value='' disabled selected>选择英雄</option>"
    for h in heroes:
        hero_list += u"<option value='%s'>%s</option>"%(h, h)
    hero_list += "</select>"
    print hero_list
    # return response
    return hero_list

@route('/get_skills_list/:name')
def skills_list(name):
    # connect sqlite db
    conn = sqlite3.connect('heroes.db')
    c = conn.cursor()
    # execute sql
    sql = 'SELECT skill1,skill2,skill3,superskill FROM heroes WHERE name="%s";'% name
    print sql
    c.execute(sql);
    row = c.fetchone()
    # close db
    conn.close()
    # construct response
    skills_list = "<ol>"
    for skill in row:
        skills_list += "<li>%s</li>"% skill
    skills_list += "</ol>"
    print skills_list
    # return response
    return skills_list

@route('/get_my_ip')
def your_ip():
    ip = request['REMOTE_ADDR']
    return ip

run(host='localhost', port=8080)
