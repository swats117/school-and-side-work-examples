import requests

client_id="96afaad4d39341bb88956fb6d17eb925"

client_secret = "3fc59800d68f4ffea37070f8a704fb65"

base_64_encoding = "OTZhZmFhZDRkMzkzNDFiYjg4OTU2ZmI2ZDE3ZWI5MjUNCg0K:M2ZjNTk4MDBkNjhmNGZmZWEzNzA3MGY4YTcwNGZiNjU"
r = requests.post("https://accounts.spotify.com/api/token", data={\
	'grant_type':'client_credentials', 'client_id':client_id, 'client_secret':client_secret})

print(r.status_code, r.reason)
print(r.text[:300] + '...')

authorization = "BQDwGvyWkdGolRN_O9DpAN8Pg8NXrgezUKEbstbLzjHBx0_Tsz7NIrmO8lIjLH-9uCEK8MhoP5Y_KBWDzoiMGdtjfgHLGoVQGUE3XDINmiXzcG1aIAERaS-Fmbpjgl-3TzQMbdelvTQCNeyqh9MeZv25KLMSHzc"
s = requests.get("https://api.spotify.com/v1/albums/0sNOF9WDwhWunNAHPD3Baj?Authorization= Bearer "+authorization)

requests.get("https://api.spotify.com/v1/albums/0sNOF9WDwhWunNAHPD3Baj", headers={"Authorization":authorization});

def make_request(string):
	s = requests.get("https://api.spotify.com/v1/search?type=track&q=track:", headers={"Authorization":"Bearer "+authorization})
	print(s.status_code, r.reason)
	print(s.text[:3000] + '...')



print("https://api.spotify.com/v1/albums/0sNOF9WDwhWunNAHPD3Baj?Authorization= Bearer " +authorization)
print(s.status_code, r.reason)
print(s.text[:300] + '...')