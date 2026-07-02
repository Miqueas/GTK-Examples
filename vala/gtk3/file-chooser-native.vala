const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.FileChooserNative";
const string APP_TITLE = "Gtk.FileChooserNative";

int main(string[] args) {
    var app = new Gtk.Application(APP_ID, 0);
    app.activate.connect(on_app_activate);
    return app.run(args);
}

void on_app_activate(Application self) {
    var native = new Gtk.FileChooserNative(APP_TITLE, null, Gtk.FileChooserAction.OPEN, "Open", "Cancel");
    native.modal = true;

    switch (native.run()) {
        case Gtk.ResponseType.ACCEPT:
        case Gtk.ResponseType.APPLY:
        case Gtk.ResponseType.YES:
        case Gtk.ResponseType.OK:
            var filename = native.get_filename();
            print(@"You selected: $(filename)\n");
            break;
        default: break;
    }

    native.destroy();
}