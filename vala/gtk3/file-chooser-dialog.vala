const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.FileChooserDialog";
const string APP_TITLE = "Gtk.FileChooserDialog";

int main(string[] args) {
    var app = new Gtk.Application(APP_ID, 0);
    app.startup.connect(on_app_startup);
    app.activate.connect(on_app_activate);
    return app.run(args);
}

void on_app_activate(Application self) {
    var app = self as Gtk.Application;
    var window = app.get_active_window();
    if (window == null) return;

    var dialog = window as Gtk.FileChooserDialog;
    var result = dialog.run();

    switch (result) {
        case Gtk.ResponseType.OK:
            var filename = dialog.get_filename();
            print(@"You selected: $(filename)\n");
            break;
        case Gtk.ResponseType.CANCEL:
            print("Canceled\n");
            break;
        default:
            print("Something else\n");
            break;
    }

    dialog.destroy();
}

void on_app_startup(Application self) {
    var app = self as Gtk.Application;
    var dialog = new Gtk.FileChooserDialog(APP_TITLE, null, Gtk.FileChooserAction.OPEN, null);
    dialog.add_button("Open", Gtk.ResponseType.OK);
    dialog.add_button("Cancel", Gtk.ResponseType.CANCEL);
    app.add_window(dialog);
}