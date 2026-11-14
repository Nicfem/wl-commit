{
  description = "Среда разработки для inputctl-dev";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
        
        clangConfig = pkgs.writeText "clang-config" ''
          CompileFlags:
            CompilationDatabase: build
            Add:
              - "-isystem${pkgs.glibc.dev}/include"
              - "-isystem${pkgs.glib.dev}/include/glib-2.0"
              - "-resource-dir=${pkgs.clang}/resource-root"
          Diagnostics:
            ClangTidy:
              Add: [modernize-use-bool-literals, bugprone-*]
        '';
      in
      {
        packages = rec {
          default = wl-commit;

          wl-commit = pkgs.stdenv.mkDerivation {
            pname = "pw-vu";
            version = "0.1";

            # Только то, что нужно для сборки библиотеки: без build/,
            # node_modules/ и прочего мусора рабочей копии.
            src = pkgs.lib.fileset.toSource {
              root = ./.;
              fileset = pkgs.lib.fileset.unions [
                ./meson.build
                ./src
              ];
            };

            mesonBuildType = "release";

            nativeBuildInputs = with pkgs; [
              meson
              ninja
              pkg-config
              gobject-introspection
            ];

            buildInputs = with pkgs; [
              glib
              gtk4
            ];
          };
        };

        devShells.default = pkgs.mkShell {
          name = "wl-commit";

          packages = with pkgs; [
            # Build
            meson
            cmake
            ninja
            pkg-config
            gobject-introspection
            nodejs_26
            gtk4
            wayland
            gjs

            # Compiler + LSP + formatting/linting
            clang
            clang-tools # clangd, clang-format, clang-tidy

            # Kernel headers (for uinput, input-event-codes.h)
            linuxHeaders
            glib
          ];

          shellHook = ''
            install -m 644 "${clangConfig}" .clangd
          '';
        };
      });
}

