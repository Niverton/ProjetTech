using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ManSuitMove : MonoBehaviour {
	// Use this for initialization
	void Start () 
	{
		
	}
	
	// Update is called once per frame
	void Update () 
	{
		if (Input.GetKeyDown(KeyCode.LeftArrow))
		{
			Vector3 position = this.transform.position;
			position.x -= 0.05f;
			this.transform.position = position;
		}

		if (Input.GetKeyDown(KeyCode.RightArrow))
		{
			Vector3 position = this.transform.position;
			position.x += 0.05f;
			this.transform.position = position;
		}

		if (Input.GetKeyDown(KeyCode.UpArrow))
		{
			Vector3 position = this.transform.position;
			position.y -= 0.05f;
			this.transform.position = position;
		}

		if (Input.GetKeyDown(KeyCode.DownArrow))
		{
			Vector3 position = this.transform.position;
			position.y += 0.05f;
			this.transform.position = position;
		}

		if (Input.GetKeyDown(KeyCode.PageUp)) 
		{
			Vector3 position = this.transform.position;
			position.z += 0.05f;
			this.transform.position = position;
		}

		if (Input.GetKeyDown(KeyCode.PageDown)) 
		{
			Vector3 position = this.transform.position;
			position.z -= 0.05f;
			this.transform.position = position;
		}
	}
}
