const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Dialog";
const string appTitle = "GtkDialog";
const string titleText = "<span size='x-large' font-weight='bold'>Universe destruction</span>";
const string summaryText = "Our universe has a lot of problems and the only way to fix it is destroying the entire universe and this important decision is now in your hands.";
const string epilogText = "<span size='large' font-weight='bold'>Do you accept?</span>";

int main(string[] args) {
  var app = new Gtk.Application(appID, ApplicationFlags.FLAGS_NONE);
  app.startup.connect(onAppStartup);
  app.activate.connect(onAppActivate);
  return app.run(args);
}

void onAppActivate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window() as Gtk.Dialog;
  var response = window?.run();
  window?.destroy();

  switch (response) {
    case Gtk.ResponseType.OK:
      print("Universe destroyed! 💥\n");
      break;
    case Gtk.ResponseType.CANCEL:
      print("Universe is in peace now! 🙏\n");
      break;
    default:
      print("Nothing happens! 🤔\n");
      break;
  }
}

void onAppStartup(Application self) {
  var dialog = new Gtk.Dialog.with_buttons(appTitle, null, Gtk.DialogFlags.MODAL,
    "Yes 😈👍", Gtk.ResponseType.OK,
    "No 💀🤚", Gtk.ResponseType.CANCEL
  );

  var titleLabel = new Gtk.Label(titleText);
  var summaryLabel = new Gtk.Label(summaryText);
  var epilogLabel = new Gtk.Label(epilogText);
  var contentBox = dialog.get_content_area();

  with (dialog) {
    title = appTitle;
    application = self as Gtk.Application;
    default_width = 400;
    border_width = 10;
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