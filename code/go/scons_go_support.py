from SCons.Script import *

archs = {'amd64': '6', '386': '8', 'arm': '5',}

def gc(source, target, env, for_signature):
    targets = target[0]
    sources = ' '.join(str(s) for s in source)
    flags = ''
    for include in env.get('GOINCLUDE', []):
        flags += '-I %s ' % (include)
    return '%s -o %s %s %s' % (env['GOCOMPILER'], targets, flags, sources)

def ld(source, target, env, for_signature):
    targets = target[0]
    sources = ' '.join(str(s) for s in source)
    return '%s -o %s %s' % (env['GOLINKER'], targets, sources)

def ar(source, target, env, for_signature):
    targets = target[0]
    sources = ' '.join(str(s) for s in source)
    return '%s %s %s' % (env['GOPACKER'], targets, sources)

def _go_object_suffix(env, sources):
    return "." + archs[env['ENV']['GOARCH']]

def _go_program_prefix(env, sources):
    return env['PROGPREFIX']

def _go_program_suffix(env, sources):
    return env['PROGSUFFIX']

go_compiler = Builder(generator=gc,
                      suffix=_go_object_suffix,
                      src_suffix='.go',)
go_linker = Builder(generator=ld,
                    prefix=_go_program_prefix,
                    suffix=_go_program_suffix,)
go_archiver = Builder(generator=ar,
                    suffix='.a',)

# Create environment
go_env = Environment(
   BUILDERS= {
      'Go': go_compiler, 
      'GoProgram': go_linker,
      'GoLib': go_archiver,
   },
   ENV=os.environ,
)

arch_prefix = archs[os.environ['GOARCH']]
go_env.SetDefault(GOCOMPILER=arch_prefix + 'g')
go_env.SetDefault(GOLINKER=arch_prefix + 'l')
go_env.SetDefault(GOPACKER='gopack grc')
