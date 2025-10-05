const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ColorChooserWidget";
const string APP_TITLE = "Gtk.ColorChooserWidget";

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
  var widget = new Gtk.ColorChooserWidget();
  var showEditorCheckButton = new Gtk.CheckButton.with_label("Show Editor");
  var printButton = new Gtk.Button.with_label("Print Color");

  window.add(box);
  window.title = APP_TITLE;
  window.border_width = 10;

  box.halign = Gtk.Align.CENTER;
  box.valign = Gtk.Align.CENTER;
  box.pack_start(widget, true, true, 0);
  box.pack_start(showEditorCheckButton, false, false, 0);
  box.pack_start(printButton, false, false, 0);
  box.show_all();

  showEditorCheckButton.active = widget.show_editor;
  showEditorCheckButton.toggled.connect((self) => {
    widget.show_editor = self.active;
  });

  printButton.clicked.connect((self) => {
    print("Color: %s\n", widget.rgba.to_string());
  });
}