const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.Assistant";
const string appTitle = "GtkAssistant";
const string deprecationTitleText = "<span size='large' weight='bold'>This widget is deprecated!</span>";
const string deprecationMessageText = "Since GTK 4.10, the GtkAssistant widget is deprecated, you should not use it anymore";

int main(string[] args) {
  var app = new Gtk.Application(appID, ApplicationFlags.FLAGS_NONE);
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
  var headerBar = new Gtk.HeaderBar();
  var deprecationTitleLabel = new Gtk.Label(deprecationTitleText);
  var deprecationMessageLabel = new Gtk.Label(deprecationMessageText);
  var mainBox = new Gtk.Box(Gtk.Orientation.VERTICAL, 0);

  with (window) {
    child = mainBox;
    titlebar = headerBar;
    set_default_size(320, 160);
  }

  titleLabel.add_css_class("title");

  with (headerBar) {
    title_widget = titleLabel;
    show_title_buttons = true;
  }

  deprecationTitleLabel.use_markup = true;

  with (deprecationMessageLabel) {
    max_width_chars = 30;
    wrap = true;
    wrap_mode = Pango.WrapMode.WORD;
  }

  with (mainBox) {
    valign = Gtk.Align.CENTER;
    halign = Gtk.Align.CENTER;
    width_request = 200;
    append(deprecationTitleLabel);
    append(deprecationMessageLabel);
  }
}