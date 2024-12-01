FROM ubuntu:24.04
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install --no-install-recommends -y \
  pip python3-venv \
&& rm -rf /var/lib/apt/lists/*
RUN mkdir /tts
WORKDIR /tts
RUN python3 -m venv .
ENV PATH="/tts/bin:$PATH"
RUN pip install coqui-tts flask torch torchaudio
COPY tts_server.py .
CMD python tts_server.py
EXPOSE 5000
