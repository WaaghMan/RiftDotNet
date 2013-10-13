namespace RiftDotNet
{
	/// <summary>
	/// ...
	/// </summary>
    public interface IProfile
	{
		/// <summary>
        /// The height of the user in meters
		/// </summary>
        float PlayerHeight { get; }

		/// <summary>
        ///Distance between eyes in meters
		/// </summary>
        float IPD { get; }
	}
}