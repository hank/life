/* WFM Decoder
 * Written by Erik Gregg
 * BSD License - just give credit
 * Takes in Rigol or other waveform (WFM) files and produces a gnuplot file.
 * Ideas and offsets stolen from http://www.mathworks.com/matlabcentral/fileexchange/18999-read-binary-rigol-waveforms
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

uint8_t chan_offsets[][3] = {
    {36, 40, 46},
    {60, 64, 70},
};

char * trigger_sources[] = {
    "CH1",
    "CH2",
    "EXT",
    "EXT/5",
    "AC Line",
    "Digital Channel",
};

char * trigger_modes[] = {
    "Edge",
    "Pulse",
    "Slope",
    "VID",
    "Alt",
    "Pattern",
    "Duration",
};

int main()
{
    union {
        uint8_t u8;
        int16_t i16;
        uint16_t u16;
        uint32_t u32;
        uint64_t u64;
        int64_t i64;
    } tmp;
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t header;
    uint8_t num_channels = 0;
    uint8_t channels = 0; // Bitfield
    uint32_t num_data_points;
    double time_scale;
    double time_delay;
    float sample_freq;
    double vertical_scaling[2];
    double vertical_position[2];
    uint16_t probe_attenuation[2];
    uint8_t * data_points[2] = {NULL, NULL};
    char * trigger_mode;
    char * trigger_source;
    FILE * out;
    char * filename;

    FILE * f = fopen("test2.wfm", "r");
    if(!f) fprintf(stderr, "Error opening file.\n");

    // Get the header bytes
    fprintf(stderr, ":: Verifying Header... ");
    if(fread(&header, 1, 2, f) < 2) goto premature_eof;
    if(header != 0xa5a5)
    {
        printf("Invalid file\n");
    }
    else fprintf(stderr, "Valid\n");

    // Read the channel booleans
    fprintf(stderr, ":: Reading # of Channels... ");
    if(fseek(f, 49, SEEK_SET) < 0)
    {
        perror("fseek");
        return 1;
    }
    if(fread(&tmp.u8, 1, 1, f) < 1) goto premature_eof;
    num_channels += tmp.u8;
    channels |= tmp.u8;
    if(fseek(f, 73, SEEK_SET) < 0)
    {
        perror("fseek");
        return 1;
    }
    if(fread(&tmp.u8, 1, 1, f) < 1) goto premature_eof;
    num_channels += tmp.u8;
    channels |= tmp.u8 << 1;

    fprintf(stderr, "%u\n", num_channels);

    // Read # of data points

    fprintf(stderr, ":: Reading # of Data Points... ");
    if(fseek(f, 28, SEEK_SET) < 0)
    {
        perror("fseek");
        return 1;
    }
    if(fread(&num_data_points, 1, 4, f) < 4) goto premature_eof;
    fprintf(stderr, "%u\n", num_data_points);

    // Read time axis

    fprintf(stderr, ":: Reading Time Axis Information...\n");
    if(fseek(f, 84, SEEK_SET) < 0)
    {
        perror("fseek");
        return 1;
    }
    if(fread(&tmp.u64, 1, 8, f) < 8) goto premature_eof;
    time_scale = tmp.u64;
    time_scale *= 1e-12;
    if(fread(&tmp.i64, 1, 8, f) < 8) goto premature_eof;
    time_delay = tmp.i64;
    time_delay *= 1e-12;

    if(fseek(f, 100, SEEK_SET) < 0)
    {
        perror("fseek");
        return 1;
    }
    if(fread(&sample_freq, 1, 4, f) < 4) goto premature_eof;

    fprintf(stderr, "\tScale: %g seconds/div\n", time_scale);
    fprintf(stderr, "\tDelay: %g\n", time_delay);
    fprintf(stderr, "\tSample Frequency: ");
    if(sample_freq < 1000) fprintf(stderr, "%f Hz\n", sample_freq);
    else if(sample_freq < 1000000) fprintf(stderr, "%f kHz\n", sample_freq / 1000);
    else if(sample_freq < 1000000000) fprintf(stderr, "%f MHz\n", sample_freq / 1000000);

    // Read channel information
    for(i=1; i<=2; ++i)
    {
        if(channels & i)
        {
            // NOTE: Probe attenuation into account for the first 2 values!
            fprintf(stderr, ":: Reading Channel %u...\n", i);

            // Probe attenuation
            if(fseek(f, chan_offsets[i-1][2], SEEK_SET) < 0)
            {
                perror("fseek");
                return 1;
            }
            if(fread(&tmp.u16, 1, 2, f) < 2) goto premature_eof;
            // Strange probe encoding...
            switch(tmp.u16)
            {
                case 0x3F80:
                  probe_attenuation[i-1] = 1;
                  break;
                case 0x4120:
                  probe_attenuation[i-1] = 10;
                  break;
                case 0x42C8:
                  probe_attenuation[i-1] = 100;
                  break;
                case 0x447A:
                  probe_attenuation[i-1] = 1000;
                  break;
                default:
                  fprintf(stderr, "Error: unknown probe attenuation.\n");
                  return 1;
            }
            
            fprintf(stderr, "\tProbe Attenuation: %u\n", 
                probe_attenuation[i-1]);

            // Vertical Scaling
            if(fseek(f, chan_offsets[i-1][0], SEEK_SET) < 0)
            {
                perror("fseek");
                return 1;
            }
            if(fread(&tmp.u32, 1, 4, f) < 4) goto premature_eof;
            vertical_scaling[i-1] = tmp.u32;
            vertical_scaling[i-1] *= 1e-6 * probe_attenuation[i-1];
            fprintf(stderr, "\tVertical Scaling: %gV/div\n", 
                vertical_scaling[i-1]);
            
            // Vertical Position
            if(fseek(f, chan_offsets[i-1][1], SEEK_SET) < 0)
            {
                perror("fseek");
                return 1;
            }
            if(fread(&tmp.i16, 1, 2, f) < 2) goto premature_eof;
            vertical_position[i-1] = tmp.i16;
            vertical_position[i-1] /= 25 * probe_attenuation[i-1];
            vertical_position[i-1] *= vertical_scaling[i-1];
            
            fprintf(stderr, "\tVertical Position: %gV\n", 
                vertical_position[i-1]);

        }
    }

    // Read data!
    if(fseek(f, 272, SEEK_SET) < 0)
    {
        perror("fseek");
        return 1;
    }
    for(i=1; i<=2; ++i)
    {
        if(channels & i)
        {
            fprintf(stderr, "Reading Channel %u data points...\n", i);
            data_points[i-1] = malloc(num_data_points * sizeof(uint8_t));
            
            if(fread(data_points[i-1], 1, num_data_points, f) < num_data_points)
            {
                goto premature_eof;
            }

            // Write data points
            if(asprintf(&filename, "tmp.%u.data", i) == -1)
            {
                fprintf(stderr, "Error: asprintf failed.\n");
            }
            out = fopen(filename, "w");
            while(j < num_data_points)
            {
                fprintf(out, "%d\n", 125 - (int)(data_points[i-1][j]));
                ++j;
            }
            fclose(out);
            free(filename);
            j = 0;
        }
    }

    // Trigger
    fprintf(stderr, ":: Reading Trigger...\n");
    if(fseek(f, 142, SEEK_SET) < 0)
    {
        perror("fseek");
        return 1;
    }
    if(fread(&tmp.u16, 1, 2, f) < 2) goto premature_eof;
    // Just get the lower 8 bits
    tmp.u16 &= 0x0F;
    trigger_mode = trigger_modes[tmp.u16];
    fprintf(stderr, "\tMode: %s\n", trigger_mode);

    if(fread(&tmp.u8, 1, 1, f) < 1) goto premature_eof;
    trigger_source = trigger_sources[tmp.u8];

    fprintf(stderr, "\tSource: %s\n", trigger_source);

    if(data_points[0]) free(data_points[0]);
    if(data_points[1]) free(data_points[1]);
    fclose(f);
    return 0;

premature_eof:
    fprintf(stderr, "Error: Premature end of file.\n");
    if(data_points[0]) free(data_points[0]);
    if(data_points[1]) free(data_points[1]);
    fclose(f);
    return 1;
}
