{ lib, stdenv, requireFile, unzip, autoPatchelfHook, jdk17, writeTextFile, buildFHSEnv, libusb1, glib, libz, libkrb5 }:

let
  version = "2.18.0";
  fileVerStr = builtins.replaceStrings [ "." ] [ "-" ] version;
in
stdenv.mkDerivation {
  inherit version;
  pname = "STM32CubeProg";

  src = requireFile rec {
    name = "en.stm32cubeprg-lin-v${fileVerStr}.zip";
    url = "https://www.st.com/en/development-tools/stm32cubeprog.html";
    message = ''
      This Nix expression requires that ${name} already be part of the store. To
      obtain it you need to navigate to ${url} and download it.

      and then add the file to the Nix store using either:

        nix-store --add-fixed sha256 ${name}

      or

        nix-prefetch-url --type sha256 file:///path/to/${name}
    '';
    sha256 = "OyMCTdqzgDouzILFcf6ujn07KSpdxnQp+IEveiA6TIw=";
  };

  nativeBuildInputs = [ unzip autoPatchelfHook ];
  buildInputs = [ jdk17 libusb1 glib libz libkrb5 ];

  unpackCmd = ''
    unzip $curSrc
    rm -r jre
    rm *.linux
    mkdir stm32inst
    mv *.exe stm32inst
  '';

  installPhase =
    let
      auto-install = writeTextFile {
        name = "auto-install.xml";
        text =
          let
            programmer = lib.boolToString true;
            packageCreator = lib.boolToString false;
          in
          ''
            <?xml version="1.0" encoding="UTF-8" standalone="no"?>
            <AutomatedInstallation langpack="eng">
                <com.st.CustomPanels.CheckedHelloPorgrammerPanel id="Hello.panel"/>
                <com.izforge.izpack.panels.info.InfoPanel id="Info.panel"/>
                <com.izforge.izpack.panels.licence.LicencePanel id="Licence.panel"/>
                <com.st.CustomPanels.TargetProgrammerPanel id="target.panel">
                    <installpath>./tmpInst</installpath>
                </com.st.CustomPanels.TargetProgrammerPanel>
                <com.st.CustomPanels.AnalyticsPanel id="analytics.panel"/>
                <com.st.CustomPanels.PacksProgrammerPanel id="Packs.panel">
                    <pack index="0" name="Core Files" selected="true"/>
                    <pack index="1" name="STM32CubeProgrammer" selected="${programmer}"/>
                    <pack index="2" name="STM32TrustedPackageCreator" selected="${packageCreator}"/>
                </com.st.CustomPanels.PacksProgrammerPanel>
                <com.izforge.izpack.panels.install.InstallPanel id="Install.panel"/>
                <com.izforge.izpack.panels.shortcut.ShortcutPanel id="Shortcut.panel">
                    <createMenuShortcuts>false</createMenuShortcuts>
                    <programGroup>STMicroelectronics\STM32CubeProgrammer</programGroup>
                    <createDesktopShortcuts>false</createDesktopShortcuts>
                    <createStartupShortcuts>false</createStartupShortcuts>
                    <shortcutType>user</shortcutType>
                </com.izforge.izpack.panels.shortcut.ShortcutPanel>
                <com.st.CustomPanels.FinishProgrammerPanel id="finish.panel"/>
            </AutomatedInstallation>
          '';
      };

      installEnv = buildFHSEnv {
        name = "installer-env";
        runScript = "java -jar SetupSTM32CubeProgrammer-${version}.exe";
      };
    in
    ''
      runHook preInstall

      mkdir $out
      substituteAll ${auto-install} auto-install.xml
      ${installEnv}/bin/${installEnv.name} auto-install.xml || echo hi
      mv ./tmpInst/* $out/

      chmod +x $out/bin/STM32*

      autoPatchelf $out/bin/STM32_Programmer_CLI
      autoPatchelf $out/bin/STM32_SigningTool_CLI
      autoPatchelf $out/bin/STM32_KeyGen_CLI

      runHook postInstall
    '';

  autoPatchelfIgnoreMissingDeps = [ "*" ];

  doCheck = true;

  meta = with lib; {
    description = "All-in-one multi-OS software tool for programming STM32 products";
    longDescription = ''
      STM32CubeProgrammer (STM32CubeProg) is an all-in-one multi-OS
      software tool for programming STM32 products.
      It provides an easy-to-use and efficient environment for reading,
      writing, and verifying device memory through both the debug interface
      (JTAG and SWD)and the bootloader interface (UART and USB DFU, I2C, SPI, and CAN).
      STM32CubeProgrammer offers a wide range of features to program STM32 internal memories
      (such as flash, RAM, and OTP) as well as external memories.
      STM32CubeProgrammer also allows option programming and upload,
      programming content verification, and programming automation through scripting.
    '';
    homepage = "https://www.st.com/en/development-tools/stm32cubeprog.html";
    license = licenses.unfree;
    platforms = [ "x86_64-linux" ];
  };
}
