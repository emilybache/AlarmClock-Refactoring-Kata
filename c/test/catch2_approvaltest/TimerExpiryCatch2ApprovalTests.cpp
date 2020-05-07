#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <climits>

#include "catch2/catch.hpp"
#include "ApprovalTests.hpp"
#include <string>

#include <memory>

auto defaultReporterDisposer =
        ApprovalTests::Approvals::useAsDefaultReporter(std::make_shared<ApprovalTests::ClipboardReporter>());


extern "C"
{
#include "timers.h"
}

std::ostream& operator<<(std::ostream& os, const struct timer_config& obj)
{
    return os
            << "operational flags: " << get_operational_flags(&obj) << "\n"
            << "reporting flags: " << get_reporting_flags(&obj) << "\n"
            << "last packet: " << get_time_of_last_pkt(&obj) << "\n";
}

TEST_CASE ("TimerExpiry", "how_long_until_next_timer_expiry") {
    // seconds since the epoch
    unsigned int now_sec = 100;
    // in-parameter for when the next timer will expire, in milliseconds after now_sec
    unsigned long min_value_ms = LONG_MAX;

    // the configuration of all the various timers
    auto *timerConfig = new timer_config();
    timerConfig->timers = new timers();
    timerConfig->timers->duration = new duration();

    how_long_until_next_timer_expiry(timerConfig, now_sec, &min_value_ms);

    std::stringstream to_approve;
    to_approve << timerConfig;
    to_approve << "NEXT_TIMER: " << min_value_ms;

    ApprovalTests::Approvals::verify(to_approve.str());
}

