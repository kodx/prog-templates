project(
    'cpp-win32-hello',
    'cpp',
    version : '0.1',
    license : 'GPLv3+',
    default_options: [
        'warning_level=3',
        'b_vscrt=static_from_buildtype',
        'buildtype=release'
    ]
)

cxx = meson.get_compiler('cpp')

project_cppflags = []
project_cpplinkargs = []

if cxx.get_id() == 'clang'
    project_cppflags = [
        '-std=c++20'
    ]
elif cxx.get_id() == 'msvc'
    project_cppflags = [
        '/std:c++latest',
    ]
endif

project_cppflags = cxx.get_supported_arguments(project_cppflags)
project_cpplinkargs = cxx.get_supported_link_arguments(project_cpplinkargs)

add_project_arguments(project_cppflags, language: 'cpp')
add_project_link_arguments(project_cpplinkargs, language: 'cpp')

project_sources = []
project_header_files = []
project_test_sources = []

inc = include_directories('src')

subdir('src')

executable(
    meson.project_name(),
    sources: project_sources,
    include_directories : inc,
    win_subsystem  : 'windows',
)

summary({
        'compiler': cxx.get_id(),
        'compiler args': project_cppflags,
        'link args': project_cpplinkargs,
        'build-type':  get_option('buildtype'),
        })

