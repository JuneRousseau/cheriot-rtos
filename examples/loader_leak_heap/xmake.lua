set_project("CHERIoT: loader leaks heap capability")
sdkdir = "../../sdk"
includes(sdkdir)
set_toolchains("cheriot-clang")

option("board")
    set_default("sail")

compartment("main")
    add_files("main.cc")

compartment("adversary")
    add_files("adversary.cc")

firmware("loader_leak_heap")
    add_deps("main", "adversary", "debug", "freestanding")
    on_load(function(target)
        target:values_set("threads", {
            {
                compartment = "main",
                priority = 1,
                entry_point = "entry",
                stack_size = 0x400,
                trusted_stack_frames = 1
            }
        }, {expand = false})
    end)
