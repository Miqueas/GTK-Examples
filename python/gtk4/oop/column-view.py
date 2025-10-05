import gi, sys
gi.require_version("Gtk", "4.0")
from gi.repository import Gtk

# Gtk.ColumnView: A widget to display data in a tabular way

class App(Gtk.Application):
    APP_ID = "io.github.Miqueas.GTK-Examples.Python.Gtk4.Procedural.ActionBar"
    APP_TITLE = "Gtk.ActionBar"

    def __init__(self):
        super().__init__(application_id = self.APP_ID)

    def do_activate(self):
        window = self.get_active_window()
        if window: window.present()

    def do_startup(self):
        # Ensures chain-up
        Gtk.Application.do_startup(self)
        
        list_model = Gtk.StringList()
        selection_model = Gtk.NoSelection(model = list_model)
        key_factory = Gtk.SignalListItemFactory()
        value_factory = Gtk.SignalListItemFactory()
        window = Gtk.ApplicationWindow(application = self, title = self.APP_TITLE)
        scroll = Gtk.ScrolledWindow()
        column_view = Gtk.ColumnView(model = selection_model)
        key_column = Gtk.ColumnViewColumn(title = "Key", factory = key_factory)
        value_column = Gtk.ColumnViewColumn(title = "Value", factory = value_factory)

        for i in range(256): list_model.append(f"{i}")

        key_factory.connect("setup", self._on_factory_setup)
        key_factory.connect("bind", self._on_factory_bind, "Key")

        value_factory.connect("setup", self._on_factory_setup)
        value_factory.connect("bind", self._on_factory_bind, "Value")

        window.set_child(scroll)
        window.set_title(self.APP_TITLE)
        window.set_default_size(400, 400)

        scroll.set_child(column_view)

        column_view.set_reorderable(False)
        column_view.set_show_row_separators(True)
        column_view.set_show_column_separators(True)
        column_view.append_column(key_column)
        column_view.append_column(value_column)

        key_column.set_expand(True)
        value_column.set_expand(True)
    
    def _on_factory_setup(self, factory, list_item):
        label = Gtk.Label()
        label.set_halign(Gtk.Align.START)
        list_item.set_child(label)

    def _on_factory_bind(self, factory, list_item, name):
        label = list_item.get_child()
        item = list_item.get_item()
        label.set_label(f"{name}: {item.get_string()}")

if __name__ == "__main__":
    sys.exit(App().run(sys.argv))