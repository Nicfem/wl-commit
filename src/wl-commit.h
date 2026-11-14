#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

/**
 * wl_commit_now:
 * @window: окно (layer-shell), у которого только что поменяли margin
 *
 * Немедленно шлёт wl_surface.commit для поверхности окна, не дожидаясь цикла
 * frame clock GDK. Ничего не делает, если окно не показано, поверхности нет
 * или GDK работает не на Wayland. Возвращает TRUE, если коммит отправлен.
 *
 * Запрос только ставится в очередь libwayland; отправка в сокет делает
 * wl_commit_flush() (или обычный flush GDK в конце итерации main loop).
 */
gboolean
wl_commit_now(GtkWindow *window);

/**
 * wl_commit_flush:
 *
 * Один раз отправляет в сокет всё, что накопилось в очереди запросов
 * (коммиты, destroy и т.д.), чтобы compositor получил это пачкой.
 */
void
wl_commit_flush(void);

G_END_DECLS
