# Array of tests to run (in order)
# Each test contains
#   description - 
#   steps - A list of steps to perform, each step can have
#       inputs - A list of tuples for the inputs to apply at that step
#       *time - The time (in ms) to wait before continuing to the next step 
#           and before checking expected values for this step. The time should be a multiple of
#           the period of the system
#       *iterations - The number of clock ticks to wait (periods)
#       expected - The expected value at the end of this step (after the "time" has elapsed.) 
#           If this value is incorrect the test will fail early before completing.
#       * only one of these should be used
#   expected - The expected output (as a list of tuples) at the end of this test
# An example set of tests is shown below. It is important to note that these tests are not "unit tests" in 
# that they are not ran in isolation but in the order shown and the state of the device is not reset or 
# altered in between executions (unless preconditions are used).
# Test sequence from waitA0: A0, !A0, A1 => PORTB: 0xF0
tests = [ {'description': 'PINA: 0x00 => PORTC: 7, state: WAIT',
    'steps': [{'inputs': [('PINA', 0x00)], 'iterations': 2}],
    'expected': [('PORTC', 7)],
    }, 
    {'description': 'PINA: 0x01 => PORTC: 8, state: WAIT_RELEASE',
    'steps': [{'inputs': [('PINA', 0x01)], 'iterations': 2}],
    'expected': [('PORTC', 8)],
    },
    {'description': 'PINA: 0x01 => PORTC: 8, state: WAIT_RELEASE',
    'steps': [{'inputs': [('PINA', 0x01)], 'iterations': 2}],
    'expected': [('PORTC', 8)],
    },
    {'description': 'PINA: 0x00 => PORTC: 8, state: WAIT',
    'steps': [{'inputs': [('PINA', 0x00)], 'iterations': 2}],
    'expected': [('PORTC', 8)],
    },
    {'description': 'PINA: 0x01 => PORTC: 9, state: WAIT_RELEASE',
    'steps': [{'inputs': [('PINA', 0x01)], 'iterations': 2}],
    'expected': [('PORTC', 9)],
    },
    {'description': 'PINA: 0x00 => PORTC: 9, state: WAIT',
    'steps': [{'inputs': [('PINA', 0x00)], 'iterations': 2}],
    'expected': [('PORTC', 9)],
    },
    {'description': 'PINA: 0x02 => PORTC: 8, state: WAIT_RELEASE',
    'steps': [{'inputs': [('PINA', 0x02)], 'iterations': 2}],
    'expected': [('PORTC', 8)],
    },
    {'description': 'PINA: 0x03 => PORTC: 0, state: RST',
    'steps': [{'inputs': [('PINA', 0x03)], 'iterations': 2}],
    'expected': [('PORTC', 0)],
    },
    {'description': 'PINA: 0x00 => PORTC: 0, state: WAIT',
    'steps': [{'inputs': [('PINA', 0x00)], 'iterations': 2}],
    'expected': [('PORTC', 0)],
    },
    {'description': 'PINA: 0x02 => PORTC: 0, state: WAIT_RELEASE',
    'steps': [{'inputs': [('PINA', 0x02)], 'iterations': 2}],
    'expected': [('PORTC', 0)],
    },
    {'description': 'PINA: 0x03 => PORTC: 0, state: RST',
    'steps': [{'inputs': [('PINA', 0x03)], 'iterations': 2}],
    'expected': [('PORTC', 0)],
    },
    {'description': 'PINA: up 2 down 1 => PORTC: 0, state: RST',
    'steps': [{'inputs': [('PINA', 0x01)], 'iterations': 2},
    {'inputs': [('PINA', 0x00)], 'iterations': 2},
    {'inputs': [('PINA', 0x01)], 'iterations': 2},
    {'inputs': [('PINA', 0x00)], 'iterations': 2},
    {'inputs': [('PINA', 0x02)], 'iterations': 2}],
    'expected': [('PORTC', 0)],
    },
    ]


# Optionally you can add a set of "watch" variables these need to be global or static and may need
# to be scoped at the function level (for static variables) if there are naming conflicts. The 
# variables listed here will display everytime you hit (and stop at) a breakpoint
watch = ['tmpA','tmpC','OUT_STATE']

