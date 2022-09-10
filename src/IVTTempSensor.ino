
const String event_prefix = "house/ivt/";
const size_t READ_BUF_SIZE = 64;

// Forward declarations
void processBuffer();

// Global variables
int counter = 0;
unsigned long lastSend = 0;
float temp = 22.0;

char readBuf[READ_BUF_SIZE];
size_t readBufOffset = 0;

void setup()
{
    Particle.publish(event_prefix + "setup", "starting", PRIVATE);
    Particle.function("setTemp", setIndoorTemp);
    delay(5000);   // Allow board to settle

    Serial1.begin(9600);

    // Init OHMIGO and sets TYPE first time. 31=IVT10K
    Serial1.printlnf("ATT=%.1f,TYPE=31", temp);
}

int setIndoorTemp(String val)
{
    String _t = String(val).trim();
    // Invalid float value becomes 0
    float newTemp = _t.toFloat();
    if (newTemp != 0 && newTemp != temp)
    {
        // Only write to IVT if temp has actually changed
        temp = newTemp;
        Serial1.printlnf("ATT=%.1f,ACK", temp);

        // Publish temp passed to OHMIGO
        char val[16];
        sprintf(val, "%.1f", temp);
        Particle.publish(event_prefix + "temp", val, PRIVATE);
    }
    return 1;
}

void loop()
{
    // Read data from serial
    while (Serial1.available())
    {
        if (readBufOffset < READ_BUF_SIZE)
        {
            char c = Serial1.read();
            if (c != '\n')
            {
                // Add character to buffer
                readBuf[readBufOffset++] = c;
            }
            else
            {
                // End of line character found, process line
                readBuf[readBufOffset] = 0;
                processBuffer();
                readBufOffset = 0;
            }
        }
        else
        {
            Serial.println("readBuf overflow, emptying buffer");
            readBufOffset = 0;
        }
    }
}

void processBuffer()
{
    // Publish ACK message from OHMIGO
    Particle.publish(event_prefix + "ohmigo/ack", readBuf, PRIVATE);
}