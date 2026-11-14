project('wl-commit', 'c', version: '0.1.0', default_options: ['c_std=gnu11', 'warning_level=2'])

gtk4 = dependency('gtk4')
gtk4_wayland = dependency('gtk4-wayland')
wayland_client = dependency('wayland-client')

lib = shared_library(
  'wl-commit',
  'src/wl-commit.c',
  dependencies: [gtk4, gtk4_wayland, wayland_client],
  install: true,
)

gnome = import('gnome')
gnome.generate_gir(
  lib,
  sources: ['src/wl-commit.c', 'src/wl-commit.h'],
  namespace: 'WlCommit',
  nsversion: '0.1',
  identifier_prefix: 'WlCommit',
  symbol_prefix: 'wl_commit',
  includes: ['Gtk-4.0'],
  header: 'wl-commit.h',
  install: true,
)
