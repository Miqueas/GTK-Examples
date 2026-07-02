const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.FileChooserButton";
const string APP_TITLE = "Gtk.FileChooserButton";

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
    var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);
    var hint_text = new Gtk.Label("Open a file");
    var button = new Gtk.FileChooserButton("", Gtk.FileChooserAction.OPEN);
    var output_text = new Gtk.Label(null);

    window.add(box);
    window.title = APP_TITLE;
    window.set_default_size(400, 400);

    box.halign = Gtk.Align.CENTER;
    box.valign = Gtk.Align.CENTER;
    box.pack_start(hint_text, false, true, 0);
    box.pack_start(button, false, true, 0);
    box.pack_start(output_text, false, true, 0);
    box.show_all();

    button.halign = Gtk.Align.CENTER;
    button.valign = Gtk.Align.CENTER;
    button.file_set.connect(() => {
        var filename = (button as Gtk.FileChooser)?.get_filename();
        output_text.label = @"Selected file: $(filename)";
    });

    output_text.set_line_wrap(true);
}