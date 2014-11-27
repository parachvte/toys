import tornado.ioloop
import tornado.web

class MainHandler(tornado.web.RequestHandler):
    def get(self):
        self.write("Hello, world")


class PostHandler(tornado.web.RequestHandler):
    def get(self, pid):
        self.write("This is a post, post id = {}".format(pid))


application = tornado.web.Application([
    (r"/", MainHandler),
    (r"/post/([0-9]+)/?", PostHandler),
])

if __name__ == "__main__":
    port = 8888
    print("Listening on port: {}".format(port))
    application.listen(port)
    tornado.ioloop.IOLoop.instance().start()


'''
in `/usr/local/lib/python3.4/site-packages/tornado-4.0.2-py3.4-macosx-10.10-x86_64.egg/tornado/web.py`:

class Application(httputil.HTTPServerConnectionDelegate):

    def __call__(self, request):
        # Legacy HTTPServer interface
        dispatcher = _RequestDispatcher(self, None)
        dispatcher.set_request(request)
        return dispatcher.execute()



class _RequestDispatcher(httputil.HTTPMessageDelegate):

    def set_request(self, request):
        self.request = request
        self._find_handler()
        self.stream_request_body = _has_stream_request_body(self.handler_class)

    def _find_handler(self):
        # Identify the handler to use as soon as we have the request.
        # Save url path arguments for later.
        app = self.application
        handlers = app._get_host_handlers(self.request)
        if not handlers:
            self.handler_class = RedirectHandler
            self.handler_kwargs = dict(url="http://" + app.default_host + "/")
            return
        for spec in handlers:
            match = spec.regex.match(self.request.path)
            if match:
                self.handler_class = spec.handler_class
                self.handler_kwargs = spec.kwargs
                if spec.regex.groups:
                    # Pass matched groups to the handler.  Since
                    # match.groups() includes both named and
                    # unnamed groups, we want to use either groups
                    # or groupdict but not both.
                    if spec.regex.groupindex:
                        self.path_kwargs = dict(
                            (str(k), _unquote_or_none(v))
                            for (k, v) in match.groupdict().items())
                    else:
                        self.path_args = [_unquote_or_none(s)
                                          for s in match.groups()]
                return
        if app.settings.get('default_handler_class'):
            self.handler_class = app.settings['default_handler_class']
            self.handler_kwargs = app.settings.get(
                'default_handler_args', {})
        else:
            self.handler_class = ErrorHandler
            self.handler_kwargs = dict(status_code=404)
'''
