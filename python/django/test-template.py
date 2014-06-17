from django import template

def test_template():
    t = template.Template('My name is {{name}}.')
    c = template.Context({'name': 'Jolly'})
    print t.render(c)
