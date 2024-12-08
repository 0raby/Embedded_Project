add_executable(${ProjectName}
    "main.c"
    "ultrasonic.c"
    "fan.c"
    "DS18B20.c"
    "pump.c"
    "waterLevel.c"
    "buzzer.c"
)
target_include_directories(${ProjectName} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${ProjectName} 
    pico_stdlib 
    FreeRTOS-Kernel-Heap4
    hardware_adc
    hardware_pwm
    hardware_spi
    hardware_i2c
    pico_binary_info)
# target_link_libraries(${projname} hardware_spi)
# target_link_libraries(${projname} hardware_i2c)
# target_link_libraries(${projname} hardware_adc)
# target_link_libraries(${projname} hardware_pwm)
# target_link_libraries(${projname} pico_binary_info)

pico_add_extra_outputs(${ProjectName})