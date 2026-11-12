set_project("CHERIoT scheduler boot stack")
sdkdir = "../../sdk"
includes(sdkdir)
set_toolchains("cheriot-clang")

option("board")
    set_default("sail")

-- Enable the scheduler's debug log by default.
option("debug-scheduler")
    set_default(true)

compartment("main")
    add_files("main.cc")

firmware("scheduler_boot_stack")
    add_deps("main", "debug", "freestanding")
    on_load(function(target)
        target:values_set("threads", {
            {
                compartment = "main",
                priority = 1,
                entry_point = "entry",
                stack_size = 0x200,
                trusted_stack_frames = 1
            }
        }, {expand = false})
    end)
