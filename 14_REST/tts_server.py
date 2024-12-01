import torch
from TTS.api import TTS
from flask import Flask, json, request, make_response
import torch
import torchaudio
from io import BytesIO

api = Flask(__name__)

@api.route('/tts', methods=['GET'])
def get_tts():
  text_got = request.args.get("text")
  wav = tts.tts(text = text_got)
  buf = BytesIO()
  torchaudio.save(buf, torch.tensor(wav).unsqueeze(0), 24000, format="wav")
  response = make_response(buf.getvalue())
  response.headers['Content-Type'] = 'audio/wav'
  response.headers['Content-Disposition'] = 'attachment; filename=sound.wav'
  buf.close()
  #print(wav)
  return response

device = "cuda" if torch.cuda.is_available() else "cpu"
tts = TTS("tts_models/hu/css10/vits").to(device)

if __name__ == '__main__':
    api.run(host = '0.0.0.0')
