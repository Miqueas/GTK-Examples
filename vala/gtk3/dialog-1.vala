const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Dialog1";
const string APP_TITLE = "Gtk.Dialog";
const string titleText = "<span size='x-large' font-weight='bold'>Universe destruction</span>";
const string epilogText = "<span size='large' font-weight='bold'>Do you accept?</span>";
const string summaryText = "Our universe has a lot of problems and the only way to fix it is by destroying it entirely and this important decision is now in your hands.";

int main(string[] args) {
  var app = new Gtk.Application(APP_ID, 0);
  app.startup.connect(on_app_startup);
  app.activate.connect(on_app_activate);
  return app.run(args);
}

void on_app_activate(Application self) {
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

void on_app_startup(Application self) {
  var dialog = new Gtk.Dialog();
  var titleLabel = new Gtk.Label(titleText);
  var summaryLabel = new Gtk.Label(summaryText);
  var epilogLabel = new Gtk.Label(epilogText);
  unowned var contentBox = dialog.get_content_area();

  dialog.title = APP_TITLE;
  dialog.application = self as Gtk.Application;
  dialog.border_width = 10;
  dialog.default_width = 400;
  dialog.add_button("Yes 👍", Gtk.ResponseType.OK);
  dialog.add_button("No 🤚", Gtk.ResponseType.CANCEL);

  titleLabel.use_markup = true;

  summaryLabel.xalign = 0;
  summaryLabel.wrap = true;
  summaryLabel.wrap_mode = Pango.WrapMode.CHAR;

  epilogLabel.use_markup = true;

  contentBox.spacing = 10;
  contentBox.pack_start(titleLabel, false);
  contentBox.pack_start(summaryLabel, false);
  contentBox.pack_start(epilogLabel, false, true, 10);
  contentBox.show_all();
}