const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Dialog2";
const string appTitle = "Gtk.Dialog";
const string titleText = "<span size='x-large' font-weight='bold'>Universe destruction</span>";
const string epilogText = "<span size='large' font-weight='bold'>Do you accept?</span>";
const string summaryText = "Our universe has a lot of problems and the only way to fix it is by destroying it entirely and this important decision is now in your hands.";

int main(string[] args) {
  var app = new Gtk.Application(appID, 0);
  app.startup.connect(onAppStartup);
  app.activate.connect(onAppActivate);
  return app.run(args);
}

void onAppActivate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window() as Gtk.Dialog;
  var response = window?.run();
  window?.destroy();

  switch (response) {
    case Gtk.ResponseType.ACCEPT:
    case Gtk.ResponseType.APPLY:
    case Gtk.ResponseType.YES:
    case Gtk.ResponseType.OK:
      print("Universe destroyed! 💥\n");
      break;
    default:
      print("Universe is in peace now! 🙏\n");
      break;
  }
}

void onAppStartup(Application self) {
  var dialog = Object.new(typeof (Gtk.Dialog), use_header_bar: true);
  unowned var headerBar = (dialog as Gtk.Dialog)?.get_header_bar();
  var titleLabel = new Gtk.Label(titleText);
  var summaryLabel = new Gtk.Label(summaryText);
  var epilogLabel = new Gtk.Label(epilogText);
  unowned var contentBox = (dialog as Gtk.Dialog)?.get_content_area();

  with (dialog as Gtk.Dialog) {
    title = appTitle;
    application = self as Gtk.Application;
    border_width = 10;
    default_width = 400;
    add_button("Yes 👍", Gtk.ResponseType.OK);
    add_button("No 🤚", Gtk.ResponseType.CANCEL);
  }

  with (headerBar) {
    title = appTitle;
    subtitle = "Example 2";
  }

  titleLabel.use_markup = true;

  with (summaryLabel) {
    xalign = 0;
    wrap = true;
    wrap_mode = Pango.WrapMode.CHAR;
  }

  epilogLabel.use_markup = true;

  with (contentBox) {
    spacing = 10;
    pack_start(titleLabel, false);
    pack_start(summaryLabel, false);
    pack_start(epilogLabel, false, true, 10);
    show_all();
  }
}