Timer Expiry Refactoring Kata
=============================

You would like to make a change to the function `how_long_until_the_next_alarm` - this change is described below. Before you make that change, you'd like to refactor the function to make it easier to make the change. (Make the change easy then make the easy change!) Before you do any refactoring, you'd like to have some test cases as insurance against mistakes.

The starting position is on the master branch, but do note there are other branches in this repo too. If you want to jump straight to the refactoring part, there is a branch 'with_tests' that has some test cases. Before you rely on them for refactoring, you should of course work out what they cover and what kinds of mistakes they will catch.

What this code does
-------------------

The `how_long_until_the_next_alarm` method should work out the number of milliseconds until the a timer will expire. It goes through six timers, named:

- idt
- p88n
- Time Quota
- zb12
- dy9x
- Monitoring Time

The code works out which timers are currently active, and how long until each one should expire. It returns the one that will expire next, (via a parameter).


The change you need to make
---------------------------

Add a new timer, named bti. This timer should be enabled when duration measurements are active and the operational flag `OPERATIONAL_FLAG_BTI_PRESENT` is set. The timer should go off when the time since the last packet is equal to `bti_time_interval`.

