#include "wl-commit.h"

#include <gdk/wayland/gdkwayland.h>
#include <wayland-client.h>

gboolean
wl_commit_now(GtkWindow *window)
{
  g_return_val_if_fail(GTK_IS_WINDOW(window), FALSE);

  GdkSurface *surface = gtk_native_get_surface(GTK_NATIVE(window));
  if (surface == NULL || !GDK_IS_WAYLAND_SURFACE(surface)) {
    return FALSE;
  }

  /* не трогаем поверхности, которые ещё не прошли начальную конфигурацию:
   * для них коммитит сам GDK */
  if (!gdk_surface_get_mapped(surface)) {
    return FALSE;
  }

  struct wl_surface *wl_surface = gdk_wayland_surface_get_wl_surface(surface);
  if (wl_surface == NULL) {
    return FALSE;
  }

  wl_surface_commit(wl_surface);
  return TRUE;
}

void
wl_commit_flush(void)
{
  GdkDisplay *display = gdk_display_get_default();
  if (display == NULL || !GDK_IS_WAYLAND_DISPLAY(display)) {
    return;
  }

  struct wl_display *wl_display = gdk_wayland_display_get_wl_display(display);
  if (wl_display != NULL) {
    wl_display_flush(wl_display);
  }
}
