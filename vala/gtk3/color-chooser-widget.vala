const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ColorChooserWidget";
const string appTitle = "Gtk.ColorChooserWidget";

int main(string[] args) {
  var app = new Gtk.Application(appID, 0);
  app.startup.connect(onAppStartup);
  app.activate.connect(onAppActivate);
  return app.run(args);
}

void onAppActivate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window();
  window?.present();
}

void onAppStartup(Application self) {
  var window = new Gtk.ApplicationWindow(self as Gtk.Application);
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);
  var widget = new Gtk.ColorChooserWidget();
  var showEditorCheckButton = new Gtk.CheckButton.with_label("Show Editor");
  var printButton = new Gtk.Button.with_label("Print Color");

  with (window) {
    add(box);
    title = appTitle;
    border_width = 10;
  }

  with (box) {
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
    pack_start(widget, true, true, 0);
    pack_start(showEditorCheckButton, false, false, 0);
    pack_start(printButton, false, false, 0);
    show_all();
  }

  showEditorCheckButton.active = widget.show_editor;
  showEditorCheckButton.toggled.connect((self) => {
    widget.show_editor = self.active;
  });

  printButton.clicked.connect((self) => {
    print("Color: %s\n", widget.rgba.to_string());
  });
}