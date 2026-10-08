set_project("CHERIoT scheduler confused deputy PoC")
sdkdir = "../../sdk"
includes(sdkdir)
set_toolchains("cheriot-clang")

option("board")
    set_default("sail")

compartment("service")
    add_files("service.cc")

compartment("client")
    add_files("client.cc")

firmware("PoC")
    add_deps("freestanding", "debug")
    add_deps("service", "client")
    on_load(function(target)
        target:values_set("threads", {
            {
                -- Highest priority, client-service thread
                compartment = "client",
                priority = 3,
                entry_point = "client_thread",
                stack_size = 0x400,
                trusted_stack_frames = 4
            },
            {
                -- Inspects the state after client-service thread executed.
                compartment = "client",
                priority = 1,
                entry_point = "client_observer_thread",
                stack_size = 0x400,
                trusted_stack_frames = 4
            }
        }, {expand = false})
    end)
