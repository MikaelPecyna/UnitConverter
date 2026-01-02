project('Convertisseur',
        'cpp',
        )

src = ['main.cpp', 'src/Lexer.cpp', 'src/Parser.cpp', 'src/Unit.cpp', 'src/Convertisseur.cpp']
lexer_src = ['src/Lexer.cpp', 'src/Unit.cpp']
parser_src = ['src/Parser.cpp']

executable('Convertisseur', src)

# Tests
test_lexer = executable(
    'test_lexer',
    ['test/test_lexer.cpp'] + lexer_src,
    include_directories: include_directories('.'),
)

test('Lexer tests', test_lexer)

test_parser = executable(
    'test_parser',
    ['test/test_parser.cpp'] + lexer_src + parser_src,
    include_directories: include_directories('.'),
)

test('Parser tests', test_parser)

