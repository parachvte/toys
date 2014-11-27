from django.http import HttpResponse


def post(request, pid):
    html = '<html><body>This is a post, post id = {}.</body></html>'.format(pid)
    return HttpResponse(html)
