const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.HeaderBar";
const string appTitle = "Gtk.HeaderBar";
const string appSubtitle = "App subtitle";

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
  var titleLabel = new Gtk.Label(appTitle);
  var subtitleLabel = new Gtk.Label(appSubtitle);
  var titleBox = new Gtk.Box(Gtk.Orientation.VERTICAL, 0);
  var header = new Gtk.HeaderBar();

  window.titlebar = header;
  window.set_default_size(400, 400);

  titleLabel.add_css_class("title");
  subtitleLabel.add_css_class("subtitle");

  titleBox.valign = Gtk.Align.CENTER;
  titleBox.append(titleLabel);
  titleBox.append(subtitleLabel);

  header.title_widget = titleBox;
  header.show_title_buttons = true;
}