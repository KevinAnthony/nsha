kikit drc run --level error coin_counter.kicad_pcb

kikit separate --source "annotation; ref: Main" coin_counter.kicad_pcb fab/main.kicad_pcb
kikit separate --source "annotation; ref: Button" coin_counter.kicad_pcb fab/button.kicad_pcb
kikit separate --source "annotation; ref: Sensor_2" coin_counter.kicad_pcb fab/sensor.kicad_pcb

kikit fab jlcpcb fab\main.kicad_pcb fab\main
rename fab\main\gerbers.zip main.zip
move fab\main\main.zip fab\main.zip

kikit fab jlcpcb fab\button.kicad_pcb fab\button
rename fab\button\gerbers.zip button.zip
move fab\button\button.zip fab\button.zip

kikit fab jlcpcb fab\sensor.kicad_pcb fab\sensor
rename fab\sensor\gerbers.zip sensor.zip
move fab\sensor\sensor.zip fab\sensor.zip