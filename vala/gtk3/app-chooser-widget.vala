const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.AppChooserWidget";
const string APP_TITLE = "Gtk.AppChooserWidget";

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
  var appChooserWidget = new Gtk.AppChooserWidget("image/png");
  var settingsLabel = new Gtk.Label("Settings");
  var showAllToggle = new Gtk.CheckButton.with_label("Show all applications");
  var showDefaultToggle = new Gtk.CheckButton.with_label("Show default");
  var showFallbackToggle = new Gtk.CheckButton.with_label("Show fallback");
  var showOtherToggle = new Gtk.CheckButton.with_label("Show other");
  var showRecommendedToggle = new Gtk.CheckButton.with_label("Show recommended");

  window.add(box);
  window.title = APP_TITLE;
  window.border_width = 10;
  window.set_default_size(400, 400);

  box.pack_start(appChooserWidget, true, true, 0);
  box.pack_start(settingsLabel, false, false, 0);
  box.pack_start(showAllToggle, false, false, 0);
  box.pack_start(showDefaultToggle, false, false, 0);
  box.pack_start(showFallbackToggle, false, false, 0);
  box.pack_start(showOtherToggle, false, false, 0);
  box.pack_start(showRecommendedToggle, false, false, 0);
  box.show_all();

  settingsLabel.halign = Gtk.Align.START;

  showAllToggle.active = appChooserWidget.show_all;
  showDefaultToggle.active = appChooserWidget.show_default;
  showFallbackToggle.active = appChooserWidget.show_fallback;
  showOtherToggle.active = appChooserWidget.show_other;
  showRecommendedToggle.active = appChooserWidget.show_recommended;

  showAllToggle.toggled.connect(self => {
    appChooserWidget.show_all = self.active;

    if (self.active) {
      showDefaultToggle.active = false;
      showFallbackToggle.active = false;
      showOtherToggle.active = false;
      showRecommendedToggle.active = false;
    }
  });

  showDefaultToggle.toggled.connect(self => {
    appChooserWidget.show_default = self.active;

    if (showAllToggle.active && self.active) showAllToggle.active = false;
  });

  showFallbackToggle.toggled.connect(self => {
    appChooserWidget.show_fallback = self.active;

    if (showAllToggle.active && self.active) showAllToggle.active = false;
  });

  showOtherToggle.toggled.connect(self => {
    appChooserWidget.show_other = self.active;

    if (showAllToggle.active && self.active) showAllToggle.active = false;
  });

  showRecommendedToggle.toggled.connect(self => {
    appChooserWidget.show_recommended = self.active;

    if (showAllToggle.active && self.active) showAllToggle.active = false;
  });
}