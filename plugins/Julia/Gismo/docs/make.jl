using Documenter, Example

push!(LOAD_PATH, "../src/")
using Gismo

DocMeta.setdocmeta!(Gismo,
                    :DocTestSetup,
                    :(using Gismo;),
                    recursive = true)

# List of subsection pages
SUBSECTION_PAGES = [
    "gsCore.md",
    "gsNurbs.md",
    "gsHSplines.md"
]

makedocs(
    sitename = "Gismo.jl",
    modules  = [Gismo],
    pages = [
        "Home" => "index.md",
        "Modules" => SUBSECTION_PAGES
    ]
)
