add_executable(
	sandbox
	"src/main.cpp"
)

set_target_properties(
	sandbox
	PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED TRUE
)

target_link_libraries(
	sandbox
	PRIVATE
	voenmath
)
