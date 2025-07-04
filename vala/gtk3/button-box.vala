const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ButtonBox";
const string appTitle = "GtkButtonBox";

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
  var buttonBox = new Gtk.ButtonBox(Gtk.Orientation.HORIZONTAL);
  var button1 = new Gtk.Button.with_label("Button 1");
  var button2 = new Gtk.Button.with_label("Button 2");
  var button3 = new Gtk.Button.with_label("Button 3");

  with (window) {
    add(buttonBox);
    title = appTitle;
    border_width = 10;
    set_default_size(400, 400);
  }

  with (buttonBox) {
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
    pack_start(button1, true, true, 0);
    pack_start(button2, true, true, 0);
    pack_start(button3, true, true, 0);
    layout_style = Gtk.ButtonBoxStyle.EXPAND;
    show_all();
  }

  button1.clicked.connect(onButtonClicked);
  button2.clicked.connect(onButtonClicked);
  button3.clicked.connect(onButtonClicked);
}

void onButtonClicked(Gtk.Button self) {
  print("%s clicked\n", self.label);
}