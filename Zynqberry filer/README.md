# Zynqberry TE0726
Forskellige demo projekter til brug på Zynqberry TE0726 board.

## ZynqHelloStandalone
Eksempel projekt til at køre et standalone program på ARM CPU og den nødvendige opsætning af FPGA'en så CPU'en kan køre med en extern timer.

Kan bruges som udgangspunkt hvis man vil hurtigt igang.
Skriver en besked på seriel (usb) porten.

## ZynqHelloFreeRTOS
Eksempel projekt til at køre et FreeRTOS system på ARM CPU og den mindst nødvendige opsætning af FPGA'en så CPU'en.

Kan bruges som udgangspunkt hvis man vil hurtigt igang.
Skriver en besked på seriel (usb) porten.

## ZynqDemoRemakeClean
Eksempel projekt til at køre petalinux OS 2021.2 på ARM CPU og til at køre en MIPI-CSI til HDMI over DMA på FPGA'en.
Indeholder precompiled petalinux til at køre fsbl og uboot på QSPI, samt kernel og rootfs på SD kort.
Indeholder også konfigurationsfilen til petalinux.
Kræver at der skrives til et register for at MIPI interfacet enables: "devmem 0x43c10040 32 1" for rasp-pi-cam v1.3.