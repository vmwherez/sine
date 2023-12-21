/* $ cc sine.c $(pkg-config --cflags --libs jack) -lm */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>
#include <jack/jack.h>
#define PI_F 3.14159265f

static jack_client_t *client = NULL;
static jack_port_t *port_out = NULL;
static volatile int done = 0;

static void
die(const char *msg)
{
  fprintf(stderr, "[error] %s\n", msg);
  if (client)
    jack_client_close(client);
  exit(EXIT_FAILURE);
}

static void
info(const char *msg)
{
  fprintf(stderr, "[info] %s\n", msg);
}

static void
on_shutdown(void *arg)
{
  client = NULL;
  die("jack server is down, exiting...");
}

static void
on_signal(int signum)
{
  done = 1;
}

static int
on_process(jack_nframes_t nframes, void *arg)
{
  static float phs = 0;
  jack_default_audio_sample_t *out;
  jack_nframes_t i;

  out = jack_port_get_buffer(port_out, nframes);
  for (i = 0; i < nframes; ++i)
  {
    out[i] = 0.1f * sinf(2 * PI_F * phs);
    phs += 0.01f;
    while (phs >= 1)
      phs--;
  }

  return 0;
}

int main(void)
{
  const char **ports;

  client = jack_client_open("sine", JackNoStartServer, NULL);
  if (!client)
    die("fail to open client");
  info("jack client opened");

  jack_on_shutdown(client, on_shutdown, NULL);
  info("shutdown callback registered");

  if (jack_set_process_callback(client, on_process, NULL))
    die("fail to set up process callback");
  info("process callback registered");

  port_out = jack_port_register(client, "out", JACK_DEFAULT_AUDIO_TYPE,
                                JackPortIsOutput, 0);
  if (!port_out)
    die("fail to register audio output port");
  info("output port registered");

  if (jack_activate(client))
    die("fail to activate client");
  info("jack client activated");

  ports = jack_get_ports(client, NULL, NULL,
                         JackPortIsInput | JackPortIsPhysical);
  if (ports)
  {
    int i;
    for (i = 0; ports[i]; ++i)
      jack_connect(client, jack_port_name(port_out), ports[i]);
    jack_free(ports);
  }

  signal(SIGINT, on_signal);
  signal(SIGTERM, on_signal);
#ifndef _WIN32
  signal(SIGQUIT, on_signal);
  signal(SIGHUP, on_signal);
#endif

  info("done! press ctrl-c to exit");

  while (!done)
    sleep(1);

  jack_deactivate(client);
  jack_client_close(client);
  return 0;
}
