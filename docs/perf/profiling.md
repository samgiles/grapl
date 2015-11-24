# Profiling

Makes use of the GeckoProfiler.

Run the application with the following environment variables:

```
# Profiler interval of 10ms
MOZ_PROFILER_INTERVAL=10

# Max profiler entries
MOZ_PROFILER_ENTRIES=100000

# On shutdown write the profile data
MOZ_PROFILER_SHUTDOWN=test.profile

# Start the profiler on startup
MOZ_PROFILER_STARTUP=1
```
