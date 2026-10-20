set_project("CHERIoT PoC register spill traps")
sdkdir = "../../sdk"
includes(sdkdir)
set_toolchains("cheriot-clang")

option("board")
    set_default("sail")

compartment("poc")
    add_files("poc.cc")

firmware("switcher_spill_fault_poc")
    add_deps("poc")
    on_load(function(target)
        target:values_set("threads", {
            {
                compartment = "poc",
                priority = 1,
                entry_point = "entry",
                stack_size = 0x200,
                trusted_stack_frames = 2
            }
        }, {expand = false})
    end)
