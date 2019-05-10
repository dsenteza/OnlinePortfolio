using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class gameController : MonoBehaviour {

    //State Tracking (to see if game over)
    public bool isGameOver;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		if(Input.GetKeyDown(KeyCode.Space) && isGameOver)
        {
            SceneManager.LoadScene("SampleScene");
        }
	}
}
