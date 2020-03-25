#include <AlarmClock.h>
#include <climits>

#include "catch2/catch.hpp"
#include "ApprovalTests.hpp"
#include <string>

namespace std {

    alarm_config *getEmptyConfig();

    string describeResult(unsigned long min_value_ms, const string &description);

    TEST_CASE ("how_long_until_the_next_alarm") {

        unsigned int now_sec = 100; // 100 seconds since the epoch
        unsigned long min_value_ms = INT_MAX;
        auto *config = getEmptyConfig();

        SECTION("no alarms set")
        {
            const char *description = "no alarms set";
            how_long_until_the_next_alarm(config, now_sec, &min_value_ms);
            ApprovalTests::Approvals::verify(describeResult(min_value_ms, description));
        }
        SECTION("idt_alarm")
        {
            std::string description = "duration measurement active, idt_alarm_time set";
            config->timers->duration->meas_active = true;
            config->timers->duration->meas_start = 50;
            config->idt_alarm_time = 190;
            config->last_pkt = 75;

            how_long_until_the_next_alarm(config, now_sec, &min_value_ms);

            ApprovalTests::Approvals::verify(describeResult(min_value_ms, description));
        }

        SECTION("P88N")
        {
            std::string description = "duration measurement active, P88N";
            config->timers->duration->meas_active = true;
            config->reporting_flags += ZJ77_REPORTING_TRIGGERS_P88N;
            config->time_threshold = 10;
            config->timers->duration->meas = 1;
            config->timers->duration->meas_start = now_sec;
            config->timers->duration->meas_threshold_used = 3;

            how_long_until_the_next_alarm(config, now_sec, &min_value_ms);

            ApprovalTests::Approvals::verify(describeResult(min_value_ms, description));
        }

        SECTION("DY9Xd")
        {
            std::string description = "DY9Xd";
            config->reporting_flags = ZJ77_REPORTING_TRIGGERS_DY9X;
            config->timers->meas_dy9xd = 5;
            config->timers->periodic_meas_start = now_sec;

            how_long_until_the_next_alarm(config, now_sec, &min_value_ms);

            ApprovalTests::Approvals::verify(describeResult(min_value_ms, description));
        }


        SECTION("monitoring_time")
        {
            config->last_pkt = 75;

            config->timers->monitoring_time_ts = 130;
            config->timers->monitoring_time_start = 99;

            how_long_until_the_next_alarm(config, now_sec, &min_value_ms);
            std::string description = "duration measurement inactive, monitoring_time";

            ApprovalTests::Approvals::verify(describeResult(min_value_ms, description));
        }

    }


    alarm_config *getEmptyConfig() {
        auto *config = new alarm_config();
        config->timers = new timers();
        config->timers->duration = new duration();
        return config;
    }

    string describeResult(unsigned long min_value_ms, const string &description) {
        std::ostringstream result;
        if (min_value_ms == INT_MAX) {
            result << description << ": INT_MAX";
        } else {
            result << description << ": " << min_value_ms;
        }
        return result.str();
    }
}