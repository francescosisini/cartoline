/**
  FILE gingle_bell.c
  Copyright (C) 2019  Francesco Sisini (francescomichelesisini@gmail.com)
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/*__________________________________________
 *
 * INSTALLAZIONE LIBRERIA
 * sudo apt-get install libopenal-dev
 * INSTALLAZIONE ESEGUIBILE
 * gcc -o gb   gingle_bell.c  -lopenal -lm
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <AL/al.h>
#include <AL/alc.h>


#define DO 261.63
#define RE 293.66
#define MI 329.63
#define FA 349.23
#define SOL 392
#define LA 440
#define SI 493.88
#define MIN 0.5

  
ALCdevice  * output;
ALCcontext * context;

ALuint i_buf;
ALuint source[1];

int aggiungi_al_buffer(short *b, int inx, float note, float val, int samplerate);
void suona();

int main() {
  
  /*_________________________________
   *
   * INIZIALIZZAZIONE
   *
   */
  
  const char * defname = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
  
  output  = alcOpenDevice(defname);
  context = alcCreateContext(output, NULL);
  alcMakeContextCurrent(context);
  
  // setup buffer and source
  
  alGenBuffers(1, & i_buf);
  for(int i = 0;i<5; i++)
    suona();


  /*_________________________________
   *
   * CONCLUSIONE
   *
   */
  
  alSourceStopv(1, &source[0]); 
  int i;
  for (i = 0; i < 1; ++i) {
    alSourcei(source[i], AL_BUFFER, 0);
  }
  
  alDeleteSources(1, &source[0]);
  alDeleteBuffers(16, &source[0]);
  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(output);
}

int aggiungi_al_buffer(short *b, int inx, float note, float val, int samplerate)
{
  size_t stop = val*samplerate;
  int i;
  for(i=inx;i<inx+stop;i++)
    {
      b[i]=32760*sin((2.f*3.14*note)/samplerate*(i-inx));
    }
  return i;
  
}

void suona()
{

  /* Fill buffer with Sine-Wave */
  float freq = 440.f;
  //float freq = 100.f;
  //float incr_freq = 0.1f;
  float incr_freq = 10.f;
  
  int seconds = 63;
  // unsigned sample_rate = 22050;
  unsigned sample_rate = 44100;
  double my_pi = 3.14159;
  size_t buf_size = seconds * sample_rate;
  
  // allocate PCM audio buffer        
  short * samples = malloc(sizeof(short) * buf_size);
  int i;
  /* ta-ta-taaa */
  i= aggiungi_al_buffer(samples, 0, MI, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN, 44100);
  /* ta-ta-taaa */
  i= aggiungi_al_buffer(samples, i, MI, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN, 44100);
  /* ta-ta-taa-ta */
  i= aggiungi_al_buffer(samples, i, MI, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, SOL, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, DO, MIN*3./4., 44100);
  i= aggiungi_al_buffer(samples, i, RE, MIN/4., 44100);
  /* taaaaaaaa*/
  i= aggiungi_al_buffer(samples, i, MI, MIN*2., 44100);
  /* ta-ta-taaa */
  i= aggiungi_al_buffer(samples, i, FA, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, FA, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, FA, MIN*3./4., 44100);
  i= aggiungi_al_buffer(samples, i, FA, MIN/4., 44100);
  /* ta-ta-taaa */
  i= aggiungi_al_buffer(samples, i, FA, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN/4., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN/4., 44100);
  /* taa taa taa taa  */
  i= aggiungi_al_buffer(samples, i, MI, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, RE, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, RE, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN/2., 44100);
  /* taaaa taaaa */
  i= aggiungi_al_buffer(samples, i, RE, MIN, 44100);
  i= aggiungi_al_buffer(samples, i, SOL, MIN, 44100);
  /* ta-ta-taaa */
  i= aggiungi_al_buffer(samples, i, MI, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN, 44100);
  /* ta-ta-taaa */
  i= aggiungi_al_buffer(samples, i, MI, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN, 44100);
     /* ta-ta-taa-ta */
  i= aggiungi_al_buffer(samples, i, MI, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, SOL, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, DO, MIN*3./4., 44100);
  i= aggiungi_al_buffer(samples, i, RE, MIN/4., 44100);
  /* taaaaaaaa*/
  i= aggiungi_al_buffer(samples, i, MI, MIN*2., 44100);
  /* taa-taa-taa-taa */
  i= aggiungi_al_buffer(samples, i, FA, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, FA, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, FA, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, FA, MIN/2., 44100);
  /* taa-taa-taa-ta-ta */
  i= aggiungi_al_buffer(samples, i, FA, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN/4., 44100);
  i= aggiungi_al_buffer(samples, i, MI, MIN/4., 44100);
  /* taa-taa-taa-taa */
  i= aggiungi_al_buffer(samples, i, SOL, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, SOL, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, FA, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, RE, MIN/2., 44100);
  /* taaaaaaaa*/
  i= aggiungi_al_buffer(samples, i, DO, MIN*2., 44100);
  
  /* inciso */
  
  /* taa-taa-taa-taa */
  i= aggiungi_al_buffer(samples, i, SOL, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, RE*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, DO*2, MIN/2., 44100);
  /* taaaaaaaa*/
  i= aggiungi_al_buffer(samples, i, SOL, MIN*2, 44100);
  /* taa-taa-taa-taa */
  i= aggiungi_al_buffer(samples, i, SOL, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, RE*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, DO*2, MIN/2., 44100);
  /* taaaaaaaa*/
  i= aggiungi_al_buffer(samples, i, LA, MIN*2, 44100);
  /* taa-taa-taa-taa */
  i= aggiungi_al_buffer(samples, i, LA, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, FA*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, RE*2, MIN/2., 44100);
  /* taaaaaaaa*/
  i= aggiungi_al_buffer(samples, i, SI, MIN*2, 44100);
  /* taa-taa-taa-taa */
  i= aggiungi_al_buffer(samples, i, SOL*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, SOL*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, RE*2, MIN/2., 44100);
  /* taaaaaaaa*/
  i= aggiungi_al_buffer(samples, i, MI*2, MIN, 44100);
  i= aggiungi_al_buffer(samples, i, DO*2, MIN, 44100);
  
  /* -------- */
  
  /* taa-taa-taa-taa */
  i= aggiungi_al_buffer(samples, i, SOL, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, RE*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, DO*2, MIN/2., 44100);
  /* taaaaaaaa*/
  i= aggiungi_al_buffer(samples, i, SOL, MIN*2, 44100);
  /* taa-taa-taa-taa */
  i= aggiungi_al_buffer(samples, i, SOL, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, RE*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, DO*2, MIN/2., 44100);
  /* taaaaaaaa*/
  i= aggiungi_al_buffer(samples, i, LA, MIN*2, 44100);
  /* taa-taa-taa-taa */
  i= aggiungi_al_buffer(samples, i, LA, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, FA*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, MI*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, RE*2, MIN/2., 44100);
  /* taaaaaaaa*/
  i= aggiungi_al_buffer(samples, i, SOL*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, SOL*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, SOL*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, SOL*2, MIN/2., 44100);
  /* taa-taa-taa-taa */
  i= aggiungi_al_buffer(samples, i, LA*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, SOL*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, FA*2, MIN/2., 44100);
  i= aggiungi_al_buffer(samples, i, RE*2, MIN/2., 44100);
  /* taaaaaaaa*/
  i= aggiungi_al_buffer(samples, i, DO*2, MIN, 44100);
    
  /* upload buffer to OpenAL */
  alBufferData( i_buf, AL_FORMAT_MONO16, samples, buf_size, sample_rate);
    
  free(samples);
  
  alGenSources(1, & source[0]);
  alSourcei(source[0], AL_BUFFER, i_buf);
    
  alSourcePlay(source[0]);
    
  ALenum state;
  alGetSourcei(source[0], AL_SOURCE_STATE, & state);
    
  while (AL_PLAYING == state)
    {
      
      alGetSourcei(source[0], AL_SOURCE_STATE, & state);
      
    }
           
}   


