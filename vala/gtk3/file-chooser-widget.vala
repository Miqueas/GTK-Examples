const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.FileChooserWidget";
const string APP_TITLE = "Gtk.FileChooserWidget";

int main(string[] args) {
    var app = new Gtk.Application(APP_ID, 0);
    app.startup.connect(on_app_startup);
    app.activate.connect(on_app_activate);
    return app.run(args);
}

void on_app_activate(Application self) {
    var window = (self as Gtk.Application)?.get_active_window();
    window?.present();
}

void on_app_startup(Application self) {
    var window = new Gtk.ApplicationWindow(self as Gtk.Application);
    var widget = new Gtk.FileChooserWidget(Gtk.FileChooserAction.OPEN);

    window.add(widget);
    window.title = APP_TITLE;
    window.set_default_size(400, 400);

    widget.show();
    widget.show_hidden.connect(() => {
        var visible = widget.get_show_hidden();
        print(@"Show hidden files: $(visible ? "Yes" : "No")\n");
    });

    widget.file_activated.connect(() => {
        var filename = widget.get_filename();
        if (filename == null) return;
        print(@"File chosen: $(filename)\n");
        window.destroy();
    });

    widget.selection_changed.connect(() => {
        var filename = widget.get_filename();
        if (filename == null) return;
        print(@"File selected: $(filename)\n");
    });
}